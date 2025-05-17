public class EnterPinState implements ATMState{

    private final ATM atm;

    private final Card card;
    public EnterPinState(ATM atm, Card card) {
        this.atm = atm;
        this.card=card;
    }


    @Override
    public void readCard(Card card) {

    }

    @Override
    public void enterPin(String pin) {

        System.out.println("Please enter your pin");

        try
        {
            BankSystem.authenticateUser(card, pin);
        }catch (IncorrectPinException e)
        {
            System.out.println("EnterredPin is incorrect");
        }


    }

    @Override
    public Transaction makeWithdrawal(int amount) {
        return null;
    }

    @Override
    public Transaction deposite(int amount) {
        return null;
    }

    @Override
    public Transaction checkBalance() {
        return null;
    }

    @Override
    public void choseTransaction() {

    }

    @Override
    public void cancel() {

    }
}
