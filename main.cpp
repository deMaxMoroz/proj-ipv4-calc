#include <iostream>
#include "ipAddress.cpp"

int main(){
  std::string ipEntered;
  short maskEntered = 24;
  ipAddress ip1;
  std::cout << "IPv4 Calculator" << std::endl;
  std::cout << "Enter IP in one of these forms:"<<std::endl;
  std::cout << "AAA.BBB.CCC.DDD" << std::endl;
  std::cout << "AAA.BBB.CCC.DDD/XX" << std::endl;
  std::cout << "IPv4: ";
  std::cin >> ipEntered;
  if (ipEntered.find("/") == std::string::npos){
    std::cout << "Default Mask Will be set - 24 (255.255.255.0)" << std::endl;
    std::cout << "Enter your mask (Press 'Enter' for Default): ";
    std::cin >> maskEntered;
    ip1 = ipAddress(ipEntered, maskEntered);
  } else {
    ip1 = ipAddress(ipEntered);
  }
  std::cout << "+ Your IPv4: ";
  ip1.printIP(); 
  std::cout << "[ Binary IPv4: " << ip1.getBinaryIP() << " ]" << '\n';
  std::cout << "#---------------------------------------------------#" << '\n';
  std::cout << "|                Choose function:                   |" << '\n';
  std::cout << "|               1. Print netmask                    |" << '\n';
  std::cout << "|               2. Print wildcard                   |" << '\n';
  std::cout << "|               3. Print network                    |" << '\n';
  std::cout << "|               4. Print broadcast                  |" << '\n';
  std::cout << "|               5. Print everything above           |" << '\n';
  std::cout << "|                                                   |" << '\n';
  std::cout << "#---------------------------------------------------#" << '\n';
  
  std::string binNetmask = ip1.getBinaryNetmask();
  int* netmaskPointer = ip1.getDecNetmask();
  
  std::string binWildcard = ip1.getBinaryWildcard();
  int* wildcardPointer = ip1.getDecWildcard();

  std::string binNetwork = ip1.getBinaryNetwork();
  int* networkPointer = ip1.getDecNetwork();

  std::string binBroadcast = ip1.getBinaryBroadcast();
  int* broadcastPointer = ip1.getDecBroadcast();

  char choice;
  std::cout << "Enter your choice: ";
  std::cin >> choice;
  while (choice < '1' || choice > '5' ){
    std::cout << "Wrong choice, try again" << '\n';
    std::cin >> choice;
  }
  switch(choice){
    case '1':
      std::cout << "[ Netmask: ";
      for (int i = 0; i < sizeof(*netmaskPointer); ++i){
        if (i == sizeof(*netmaskPointer) - 1) { 
          std::cout << *(netmaskPointer + i);
          break;
        }
        std::cout << *(netmaskPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Netmask: " << binNetmask << " ] " << '\n';
      break;
    case '2':
      std::cout << "[ Wildcard: ";
      for (int i = 0; i < sizeof(*wildcardPointer); ++i){
        if (i == sizeof(*wildcardPointer) - 1) { 
          std::cout << *(wildcardPointer + i);
          break;
        }
        std::cout << *(wildcardPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Wildcard: " << binWildcard << " ] " << '\n';
      break;
    case '3':
      std::cout << "[ Network: ";
      for (int i = 0; i < sizeof(*networkPointer); ++i){
        if (i == sizeof(*networkPointer) - 1) { 
          std::cout << *(networkPointer + i);
          break;
        }
        std::cout << *(networkPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Network: " << binNetwork << " ] " << '\n';
      break;
    case '4':
      std::cout << "[ Broadcast: ";
      for (int i = 0; i < sizeof(*broadcastPointer); ++i){
        if (i == sizeof(*broadcastPointer) - 1) { 
          std::cout << *(broadcastPointer + i);
          break;
        }
        std::cout << *(broadcastPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Broadcast: " << binBroadcast << " ] " << '\n';
      break;
    case '5':
      std::cout << "[ Netmask: ";
      for (int i = 0; i < sizeof(*netmaskPointer); ++i){
        if (i == sizeof(*netmaskPointer) - 1) { 
          std::cout << *(netmaskPointer + i);
          break;
        }
        std::cout << *(netmaskPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Netmask: " << binNetmask << " ] " << '\n';
      std::cout << "[ Wildcard: ";
      for (int i = 0; i < sizeof(*wildcardPointer); ++i){
        if (i == sizeof(*wildcardPointer) - 1) { 
          std::cout << *(wildcardPointer + i);
          break;
        }
        std::cout << *(wildcardPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Wildcard: " << binWildcard << " ] " << '\n';
      std::cout << "[ Network: ";
      for (int i = 0; i < sizeof(*networkPointer); ++i){
        if (i == sizeof(*networkPointer) - 1) { 
          std::cout << *(networkPointer + i);
          break;
        }
        std::cout << *(networkPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Network: " << binNetwork << " ] " << '\n';
      std::cout << "[ Broadcast: ";
      for (int i = 0; i < sizeof(*broadcastPointer); ++i){
        if (i == sizeof(*broadcastPointer) - 1) { 
          std::cout << *(broadcastPointer + i);
          break;
        }
        std::cout << *(broadcastPointer + i) << ".";
      }
      std::cout << " ] . [ Binary Broadcast: " << binBroadcast << " ] " << '\n';
      break;
    default:
      break;

  }
  char exit;
  std::cout << "Enter any symbol and hit Enter to exit program" << '\n';
  std::cin >> exit;
  return 0;
}
