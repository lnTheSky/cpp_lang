#include "ProcessControlBlock.h"
namespace ProcessControlBlock {
    ListNode::ListNode(const PCB& data, ListNode* nextNode)
        : data(data), next(nextNode)
    {
    }

    ProcessList::ProcessList()
        : head(nullptr)
    {
    }

    ProcessList::~ProcessList()
    {
        while (head != nullptr) {
            ListNode* to_delete = head;
            head = head->next;
            delete to_delete;
        }
    }

    bool ProcessList::insert(const PCB& newPCB)
    {
        if (head == nullptr || newPCB.processID < head->data.processID)
        {
            head = new ListNode(newPCB, head);
            return true;
        }

        ListNode* cur = head;
        while (cur->next && cur->next->data.processID < newPCB.processID)
        {
            cur = cur->next;
        }

        if ((cur->data.processID == newPCB.processID) ||
            (cur->next && cur->next->data.processID == newPCB.processID))
        {
            return false;
        }

        cur->next = new ListNode(newPCB, cur->next);
        return true;
    }

    bool ProcessControlBlock::ProcessList::remove(unsigned short pid)
    {
        if (head == nullptr) return false;

        if (head->data.processID == pid)
        {
            ListNode* to_delete = head;
            head = head->next;
            delete to_delete;
            return true;
        }

        ListNode* cur = head;
        while (cur->next && cur->next->data.processID < pid)
        {
            cur = cur->next;
        }

        if (cur->next && cur->next->data.processID == pid)
        {
            ListNode* to_delete = cur->next;
            cur->next = cur->next->next;
            delete to_delete;
            return true;
        }

        return false;
    }

    void ProcessControlBlock::ProcessList::printList()
    {
        if (head == nullptr)
        {
            std::cout << "Process list is empty!" << std::endl;
            return;
        }

        ListNode* cur = head;
        std::cout << "Process list:" << std::endl;
        while (cur)
        {
            const PCB& pcb = cur->data;
            std::cout << "{ PID: " << pcb.processID 
                    << ", Name: " << pcb.processName 
                    << ", Status: ";
            switch (pcb.processStatus)
            {
                case Status::Running: std::cout << "Running"; break;
                case Status::Waiting: std::cout << "Waiting"; break;
                case Status::Stopped: std::cout << "Stopped"; break;
            }
            std::cout << ", CommandCounter: " << pcb.commandCounter << " }" << std::endl;

            cur = cur->next;
        }
    }

}