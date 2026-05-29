#include "commands/ConnectCommand.h"
#include "NetworkManager.h"
#include "EthernetBus.h"
#include "Node.h"
#include <iostream>

// CONNECT(node1, node2)
void ConnectCommand::execute(const std::vector<std::string> &args, NetworkManager &netManager)
{
     if (args.size() < 4)
     {
          return;
     }
     Node *node1 = netManager.getNode(args[2]);
     Node *node2 = netManager.getNode(args[4]);

     if (node1 && node2)
     {
          if (!node1->getInterfaces("unconnected").empty() && !node2->getInterfaces("unconnected").empty())
          {
               auto cable = std::make_unique<EthernetBus>();
               cable->connect(node1->getInterfaces("unconnected").at(0));
               cable->connect(node2->getInterfaces("unconnected").at(0));

               netManager.addTickable(cable.get());
               netManager.addCable(std::move(cable));
          }
          else
          {
               std::cout << "Error: One of the nodes has no free interface." << std::endl;
          }
     }
}