/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/09 9:07
  filename:  AriesGames\BomberManClient\src\network\net_client.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <SDL3/SDL.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten/websocket.h>
#else
//#include <SDL3_net/SDL_net.h>
#endif

#include "network/net_client.h"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

struct SocketHanler {
#if defined(__EMSCRIPTEN__)
  EMSCRIPTEN_WEBSOCKET_T handle = -1;
#else
  //NET_StreamSocket* handle = nullptr;
#endif
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

NetClient::NetClient() : socket_(new SocketHanler()) {
#if !defined(__EMSCRIPTEN__)
  // NET_Init();
#endif
}
// -----------------------------------------------------------------------------

NetClient::~NetClient() {
  delete static_cast<SocketHanler*>(socket_);
#if !defined(__EMSCRIPTEN__)
  // NET_Quit();
#endif
}
// -----------------------------------------------------------------------------

bool NetClient::Connect(const std::string& ip, int port) {
  SocketHanler *socket = static_cast<SocketHanler*>(socket_);

  ip_ = ip;
  port_ = port;

#if defined(__EMSCRIPTEN__)
  auto on_open = [](int, const EmscriptenWebSocketOpenEvent* e, void* user) {
    NetClient* This = reinterpret_cast<NetClient*>(user);
    This->OnConnected();
    return EM_TRUE;
  };

  auto on_message = [](int, const EmscriptenWebSocketMessageEvent* e, void* user) {
    NetClient* This = reinterpret_cast<NetClient*>(user);
    This->OnDataRecv(e->data, e->numBytes);
    return EM_TRUE;
  };

  auto on_error = [](int, const EmscriptenWebSocketErrorEvent* e, void* user) {
    NetClient* This = reinterpret_cast<NetClient*>(user);
    This->OnError(-1, "WebSocket error");
    return EM_TRUE;
  };

  auto on_close = [](int, const EmscriptenWebSocketCloseEvent* e, void* user) {
    NetClient* This = reinterpret_cast<NetClient*>(user);
    This->OnDisconnected();
    return EM_TRUE;
  };

  std::string url("ws://" + ip_ + ":" + std::to_string(port_));

  EmscriptenWebSocketCreateAttributes attr;
  emscripten_websocket_init_create_attributes(&attr);
  attr.url = url.c_str();
  attr.createOnMainThread = true;
  socket->handle = emscripten_websocket_new(&attr);
  if (socket->handle <= 0) {
    return false;
  }

  emscripten_websocket_set_onopen_callback(socket->handle, this, on_open);
  emscripten_websocket_set_onmessage_callback(socket->handle, this, on_message);
  emscripten_websocket_set_onerror_callback(socket->handle, this, on_error);
  emscripten_websocket_set_onclose_callback(socket->handle, this, on_close);

#else

  // NET_Address* addr = NET_ResolveHostname(ip_.c_str());
  // if (NET_WaitUntilResolved(addr, 5000) == NET_FAILURE) {
  //   SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to resolve hostname %s: %s", ip_.c_str(), SDL_GetError());
  //   return false;
  // }

  // socket->handle = NET_CreateClient(addr, port_);
  // if (!socket->handle) {
  //   SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create stream socket to %s:%d: %s", ip_.c_str(), port_, SDL_GetError());
  //   return false;
  // }

  // if (NET_WaitUntilConnected(socket->handle, 5000) == NET_FAILURE) {
  //   SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to connect to %s:%d: %s", ip_.c_str(), port_, SDL_GetError());
  //   NET_DestroyStreamSocket(socket->handle);
  //   socket->handle = nullptr;
  //   return false;
  // }
#endif

  return true;
}
// -----------------------------------------------------------------------------

void NetClient::Disconnect() {
  SocketHanler *socket = static_cast<SocketHanler*>(socket_);

#if defined(__EMSCRIPTEN__)
  if (socket->handle > 0) {
    emscripten_websocket_close(socket->handle, 1000, "Normal Closure");
    socket->handle = -1;
  }
#else
  // if (socket->handle) {
  //   NET_DestroyStreamSocket(socket->handle);
  //   socket->handle = nullptr;
  // }
#endif
}
// -----------------------------------------------------------------------------

void NetClient::OnConnected() {

}
// -----------------------------------------------------------------------------

void NetClient::OnDisconnected() {

}
// -----------------------------------------------------------------------------

void NetClient::OnError(int error_code, const std::string& error_message) {
  //SDL_LogError(error_code, "%s", error_message.c_str());
}
// -----------------------------------------------------------------------------

void NetClient::OnDataRecv(const uint8_t* data, size_t length) {
  
}
// -----------------------------------------------------------------------------
