public class ATM {

    private final String atmID;

    private ATMState state;

    public void changeState(ATMState newState)
    {
        state=newState;
    }

    public ATM(String atmID) {
        this.atmID = atmID;
    }
}
