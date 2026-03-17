#include <vector>
#include <string>

// this will all be replaced with actual objects (.i.e. LAN object)
class NetworkManager {
    public:
    void addLAN(std::string LAN_name);
    void printLANs();
    
    private:
    std::vector<std::string> LAN_list;
};