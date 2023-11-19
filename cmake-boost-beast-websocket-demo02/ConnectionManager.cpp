#include "ConnectionManager.h"

ConnectionManager &ConnectionManager::GetInstance() {
  static ConnectionManager instance;
  return instance;
}

void ConnectionManager::AddConnection(std::shared_ptr<Connection> conptr) {
  _map_cons[conptr->GetUid()] = conptr;
}

void ConnectionManager::RmvConnection(std::string id) {
  _map_cons.erase(id);
}

ConnectionManager::ConnectionManager() {

}
