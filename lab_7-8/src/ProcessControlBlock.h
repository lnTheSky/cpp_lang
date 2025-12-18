#include <string>
#include <cstdint>
#include <iostream>

namespace ProcessControlBlock
{
    enum class Status
    {
        Running,
        Waiting,
        Stopped
    };

    struct Registers
    {
        // Данные/счётчики
        uint64_t rax = 0;
        uint64_t rbx = 0;
        uint64_t rcx = 0;
        uint64_t rdx = 0;

        // Работа со строками
        uint64_t rsi = 0;
        uint64_t rdi = 0;

        // Стек
        uint64_t rbp = 0;
        uint64_t rsp = 0;

        // Регистры общего назначения
        uint64_t r8 = 0;
        uint64_t r9 = 0;
        uint64_t r10 = 0;
        uint64_t r11 = 0;
        uint64_t r12 = 0;
        uint64_t r13 = 0;
        uint64_t r14 = 0;
        uint64_t r15 = 0;

        // Следующая инструкция
        uint64_t rip = 0;

        // Флаги процессора
        uint64_t rflags = 0;
    };

    struct PCB
    {
        unsigned short  processID;
        std::string     processName;
        Status          processStatus;
        int             commandCounter;
        Registers       cpuRegisters;
    };

    // Я бы сделал структурой
    struct ListNode
    {
        PCB       data;
        ListNode* next;
    };

    class ProcessList
    {
        ListNode* head;
    public:
        ProcessList();
        ~ProcessList();

        bool insert(const PCB& newPCB);
        bool remove(unsigned short pid);
        void printList();
    };
};