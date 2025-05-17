public class ReadyState implements ATMState{

    private final ATM atm;

    public ReadyState(ATM atm) {
        this.atm = atm;
    }

    @Override
    public void readCard(Card card) {

        System.out.println("Please insert the card");
        CardReader.isValidCard(card);

        atm.changeState(new EnterPinState(this.atm,card));

    }

    @Override
    public void enterPin(String pin) {

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
