public interface ATMState {

    public void readCard(Card card);
    public void enterPin(String pin);
    public Transaction makeWithdrawal(int amount);
    public Transaction deposite(int amount);
    public Transaction checkBalance();
    public void choseTransaction();
    public void cancel();


}
