#include "ProcessControlBlock.h"

using namespace ProcessControlBlock;

int main() {
    std::cout << "Initializing ProcessList" << std::endl << std::endl;

    ProcessList plist;

    PCB process_1;
    process_1.processID = 676;
    process_1.commandCounter = 0;
    process_1.processName = "Process 1";
    process_1.processStatus = Status::Running;

    PCB process_2;
    process_2.processID = 30241;
    process_2.commandCounter = 0;
    process_2.processName = "Process 2";
    process_2.processStatus = Status::Stopped;

    PCB process_3;
    process_3.processID = 1002;
    process_3.commandCounter = 0;
    process_3.processName = "Process 3";
    process_3.processStatus = Status::Waiting;


    plist.insert(process_1);
    plist.insert(process_2);
    plist.insert(process_3);

    plist.printList();

    plist.remove(1002);

    std::cout << std::endl;
    plist.printList();

    std::cout << "Inserting duplcate of Process 1: " << plist.insert(process_1) << std::endl;
    std::cout << "Removing non-existent Process 3: " << plist.remove(1002) << std::endl << std::endl;

    plist.printList();

}