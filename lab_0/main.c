#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 1000

typedef struct {
    char date[11];
    char category[30];
    float amount;
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

void loadExpenses(const char *filename)
{
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        return;
    }

    while (expenseCount < MAX_EXPENSES &&
           fscanf(fin, "%10s %29s %f", 
                  expenses[expenseCount].date,
                  expenses[expenseCount].category,
                  &expenses[expenseCount].amount) == 3) {
        expenseCount++;
    }

    fclose(fin);
}

void saveExpenseToFile(const char *filename, Expense e)
{
    FILE *fout = fopen(filename, "a");
    if (!fout) {
        printf("Error while saving to file!\n");
        return;
    }

    fprintf(fout, "%s %s %.2f\n", e.date, e.category, e.amount);
    fclose(fout);
}

void addExpense()
{
    if (expenseCount >= MAX_EXPENSES)
    {
        printf("Expenses limit exceeded!\n");
        return;
    }

    Expense e;

    printf("Enter date (dd.mm.yyyy): ");
    scanf("%s", &e.date);

    printf("Enter category: ");
    scanf("%s", &e.category);

    printf("Enter amount: ");
    scanf("%f", &e.amount);

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    printf("Expense added!\n");
}

void showAllExpenses()
{
    if (expenseCount == 0)
    {
        printf("No expense info\n");
        return;
    }

    printf("\n--- All expenses ---\n");
    printf("%-12s%-15sAmount\n", "Date", "Category");
    printf("------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        printf("%-12s%-15s%.2f rub.\n", 
            expenses[i].date, 
            expenses[i].category, 
            expenses[i].amount);
    }
}

void showStats()
{
    if (expenseCount == 0)
    {
        printf("No analysis data\n");
        return;
    }

    float total = 0;
    float max = expenses[0].amount;

    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;

        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount;

    printf("\n--- Statistics ---\n");
    printf("Total spent: %f rub.\n", total);
    printf("Average expense: %f rub.\n", average);
    printf("Max expense: %f rub.\n", max);
}

void showMenu()
{
    printf("\n=== Expenses tracker ===\n");
    printf("1. Add expense\n");
    printf("2. Show all expenses\n");
    printf("3. Show statistics\n");
    printf("4. exit\n");
    printf("Choose option: ");
}

int main()
{
    loadExpenses("expenses.txt");

    int choice;

    do
    {
        showMenu();
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            addExpense();
            break;
        case 2:
            showAllExpenses();
            break;
        case 3:
            showStats();
            break;
        case 4:
            printf("Exitting...\n");
            break;
        default:
            printf("Wrong option!\n");
        }

    } while (choice != 4);

    return 0;
}
