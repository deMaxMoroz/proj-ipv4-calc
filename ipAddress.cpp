#include <string>
#include <iostream>
#include <cmath> 
#include <bits/stdc++.h>

class ipAddress{
public:
  ipAddress(){};
  ipAddress(std::string ipValueFull){
    if (ipValueFull.length()<7 || ipValueFull.length()>18){
      std::cout << "Not a Valid IP" << std::endl;
      return;
    }
    std::string maskStr = ipValueFull.substr(ipValueFull.find("/") + 1, 2);
   
    for (const auto& c : maskStr){
        this->netmask = this->netmask*10 + (c - '0');
    }
    if (this->netmask < 0) this->netmask += 32;
    if (this->netmask>32) this->netmask -= 32;

    std::string ipValue = ipValueFull.substr(0, ipValueFull.length() - maskStr.length());
    int tmp = 0;
    int count = 0;
    for (const auto& c : ipValue){
      if (c >= '0' && c <= '9'){
        tmp = tmp*10 + (c - '0');

      }else{
        if (tmp>255 || tmp <0){
          std::cout << "Not a valid ip!" << std::endl;
          return;
        }
        octets[count++] = tmp;
        tmp = 0;
      }
    }
  };


  ipAddress(std::string ipValue, short netmask){
    if (netmask < 0) this->netmask += 32;
    if (netmask>32) this->netmask -= 32;
    this->netmask = netmask;
    int tmp = 0;
    int count = 0;
    for (const auto& c : ipValue+"/"){

      if (c >= '0' && c <= '9'){
        tmp = tmp*10 + (c - '0');

      } else {
        if (tmp>255 || tmp <0){
          std::cout << "Not a valid ip!" << std::endl;
          return;
        }
        octets[count++] = tmp;

        tmp = 0;
      }

    }
  };

  void printIP() const{
    for (size_t i = 0; i < std::size(this->octets); ++i){

      if (i == std::size(this->octets)-1){
        std::cout << this->octets[i] << "/" << this->netmask << std::endl;
        return;
      }
      std::cout << this->octets[i]<<".";
    }
  }

  std::string decToBin(int octet) {
    short asciicode = 48;
    std::string bin;

    while (octet > 0){
      bin += (char) octet%2 + asciicode;
      octet /= 2;
    }
    std::reverse(bin.begin(), bin.end());
    while (bin.length() < 8){
      bin = "0" + bin;
    }
    return bin;
  }

  int binToDec(std::string binary){
    int res = 0;
    // std::cout << "----- DEBUG BIN TO DEC -----" << '\n';
    for (int i = 0; i < binary.length(); ++i){
       // std::cout << "i = " << i << '\n';
        //std::cout << "char to int = " << (binary[i] - '0')  << '\n';
        //std::cout << "power 2 ** i = " << pow(2,binary.length() - i - 1) << '\n';
        res += (int)(binary[i] - '0') * (int) pow(2, binary.length() - i - 1);
         //std::cout << "res =  " << res << '\n';
    }
     //std::cout << "----- DEBUG BIN TO DEC END -----" << '\n';
    return res;
  }
  
  std::string& getBinaryIP(){ 
    for (int i = 0; i < std::size(this->octets);++i){
      if (i == std::size(this->octets) - 1){
        this->binaryIp.append(decToBin(this->octets[i]));
        break;
      }
      this->binaryIp.append(decToBin(this->octets[i]) + ".");
    }
    int indOfdel = netmask / 8;
    if (netmask == 32) indOfdel = 3;
   // this->binaryIp.insert(netmask + indOfdel, "|");
    if (this->binaryIp[netmask + indOfdel - 1] == '.'){
      this->binaryIp.replace(netmask + indOfdel - 1, 1, "|");
    } else {
      this->binaryIp.insert(netmask + indOfdel, "|");
    }
    return binaryIp;
  }

  std::string& getBinaryNetmask(){
    std::string binaryIpCopy = this->binaryIp;

    std::size_t maskIndex = binaryIpCopy.find("|");

    std::string beforeMask = binaryIpCopy.substr(0, maskIndex); 
    std::replace(beforeMask.begin(), beforeMask.end(), '0', '1');

    std::string afterMask = binaryIpCopy.substr(maskIndex + 1, this->binaryIp.length() - maskIndex);
    std::replace(afterMask.begin(), afterMask.end(), '1', '0');

    this->binaryNetmask = beforeMask + afterMask;
    this->binaryNetmask.insert(maskIndex, "|");
    
    return binaryNetmask;
  }

  int* getDecNetmask(){
    std::string binNetmaskCopy = this->binaryNetmask;

    while (true) {
        std::size_t pos = binNetmaskCopy.find('.');
        if (pos == std::string::npos) break; 
        binNetmaskCopy.replace(pos, 1, "");
    }

    std::size_t maskIndex = binNetmaskCopy.find("|");
    binNetmaskCopy.replace(maskIndex, 1, "");

    int ind = 0;
    for (int i = 0; i < std::size(this->netmaskOcts); ++i){
      //std::cout << "---- GET DEC NETMASK START ------" << '\n';
      //std::cout << "sub = (ind, ind+8) = " << binNetmaskCopy.substr(ind, 8) << '\n';
      this->netmaskOcts[i] = binToDec(binNetmaskCopy.substr(ind, 8));
      ind += 8;
      //std::cout << "netOCt[i] = " << this->netmaskOcts[i] << '\n';
      //std::cout << "i = " << i << '\n';
      //std::cout << "---- GET DEC NETMASK END ------" << '\n';
    }
    return netmaskOcts;
  }

  std::string& getBinaryWildcard(){
    std::string binaryIpCopy = this->binaryIp;

    std::size_t maskIndex = binaryIpCopy.find("|");

    std::string beforeMask = binaryIpCopy.substr(0, maskIndex); 
    std::replace(beforeMask.begin(), beforeMask.end(), '1', '0');

    std::string afterMask = binaryIpCopy.substr(maskIndex + 1, this->binaryIp.length() - maskIndex);
    std::replace(afterMask.begin(), afterMask.end(), '0', '1');

    this->binaryWildcard = beforeMask + afterMask;
    this->binaryWildcard.insert(maskIndex, "|");
    
    return binaryWildcard;
  }

  
  int* getDecWildcard(){
    std::string binWildcardCopy = this->binaryWildcard;

    while (true) {
        std::size_t pos = binWildcardCopy.find('.');
        if (pos == std::string::npos) break; 
        binWildcardCopy.replace(pos, 1, "");
    }

    std::size_t maskIndex = binWildcardCopy.find("|");
    binWildcardCopy.replace(maskIndex, 1, "");

    int ind = 0;
    for (int i = 0; i < std::size(this->wildcardOcts); ++i){
      //std::cout << "---- GET DEC NETMASK START ------" << '\n';
      //std::cout << "sub = (ind, ind+8) = " << binNetmaskCopy.substr(ind, 8) << '\n';
      this->wildcardOcts[i] = binToDec(binWildcardCopy.substr(ind, 8));
      ind += 8;
      //std::cout << "netOCt[i] = " << this->netmaskOcts[i] << '\n';
      //std::cout << "i = " << i << '\n';
      //std::cout << "---- GET DEC NETMASK END ------" << '\n';
    }
    return wildcardOcts;
  }

  std::string& getBinaryNetwork(){
    std::string binaryIpCopy = this->binaryIp;

    std::size_t maskIndex = binaryIpCopy.find("|");

    std::string beforeMask = binaryIpCopy.substr(0, maskIndex + 1);

    std::string afterMask = binaryIpCopy.substr(maskIndex + 1, this->binaryIp.length() - maskIndex);
    std::replace(afterMask.begin(), afterMask.end(), '1', '0');

    this->binaryNetwork = beforeMask + afterMask;
    
    return binaryNetwork;
  }

  int* getDecNetwork(){
    std::string binNetworkCopy = this->binaryNetwork;

    while (true) {
        std::size_t pos = binNetworkCopy.find('.');
        if (pos == std::string::npos) break; 
        binNetworkCopy.replace(pos, 1, "");
    }

    std::size_t maskIndex = binNetworkCopy.find("|");
    binNetworkCopy.replace(maskIndex, 1, "");

    int ind = 0;
    for (int i = 0; i < std::size(this->networkOcts); ++i){

      this->networkOcts[i] = binToDec(binNetworkCopy.substr(ind, 8));
      ind += 8;
    }
    return networkOcts;
  }


  std::string& getBinaryBroadcast(){
    std::string binaryIpCopy = this->binaryIp;

    std::size_t maskIndex = binaryIpCopy.find("|");

    std::string beforeMask = binaryIpCopy.substr(0, maskIndex + 1); 

    std::string afterMask = binaryIpCopy.substr(maskIndex + 1, this->binaryIp.length() - maskIndex);
    std::replace(afterMask.begin(), afterMask.end(), '0', '1');

    this->binaryBroadcast = beforeMask + afterMask;
    
    return binaryBroadcast;
  }

  int* getDecBroadcast(){
    std::string binaryBroadcastCopy = this->binaryBroadcast;

    while (true) {
        std::size_t pos = binaryBroadcastCopy.find('.');
        if (pos == std::string::npos) break; 
        binaryBroadcastCopy.replace(pos, 1, "");
    }

    std::size_t maskIndex = binaryBroadcastCopy.find("|");
    binaryBroadcastCopy.replace(maskIndex, 1, "");

    int ind = 0;
    for (int i = 0; i < std::size(this->broadcastOcts); ++i){

      this->broadcastOcts[i] = binToDec(binaryBroadcastCopy.substr(ind, 8));
      ind += 8;
    }
    return broadcastOcts;
  }

private:
  int octets[4];
  int netmaskOcts[4];
  int wildcardOcts[4];
  int networkOcts[4];
  int broadcastOcts[4];
  short netmask = 0;
  std::string binaryIp, binaryNetwork, binaryWildcard, binaryNetmask, binaryBroadcast;
  int minHost,maxHost,hosts;

};
