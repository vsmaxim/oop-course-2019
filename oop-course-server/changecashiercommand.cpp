#include "changecashiercommand.h"


ChangeCashierCommand::ChangeCashierCommand(model &m, cashierId id, double newMean) : ModelCommand(m),
    cashier(id), newMean(newMean)
{

}

void ChangeCashierCommand::execute()
{
    if (cashier == 1)
    {
        targetModel.setFirstCustomerMean(newMean);
    } else
    {
        targetModel.setSecondCustomerMean(newMean);
    }
}
