import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.max;
import static java.lang.Math.min;

public class Elevator {

    private String state;
    private final int elevatorID;
    private ElevatorManager manager;
    List<Boolean> floorList = new ArrayList<>(Constants.MAX_FLOOR);

    List<Integer> pendingRequest = new ArrayList<>();
    int finalFloor;
    int currFloor;


    public Elevator(String state, int elevatorID, ElevatorManager manager, List<Boolean> floorList, int currFloor) {
        this.state = state;
        this.elevatorID = elevatorID;
        this.manager = manager;
        this.floorList = floorList;
        this.finalFloor = currFloor;
        this.currFloor = currFloor;
    }

    public void addUpFloor(int floor)
    {
        finalFloor=max(finalFloor,floor);
        floorList.set(floor, true);
    }

    public void addDownFloor(int floor)
    {
        finalFloor=min(finalFloor,floor);
        floorList.set(floor,true);
    }

    public void move() throws InterruptedException {
        Thread.sleep(5000);
        if(state.equals("MOVING_UP") || state.equals("MOVING_UP_PICK"))
        {
            currFloor++;

        }
        else if(state.equals("MOVING_DOWN") || state.equals("MOVING_DOWN_PICK")){
            currFloor--;
        }
        if(currFloor>=0 && currFloor<floorList.size() && floorList.get(currFloor))
        {
            floorList.set(currFloor,false);
        }

        if(currFloor==finalFloor)
        {
            if(pendingRequest.size()==0)
            {
                state="IDLE";
                manager.notifyIDLE(this);
            }
            else{

                if(state.equals("MOVING_DOWN"))
                {
                    state="MOVING_UP";

                    for(Integer a: pendingRequest)
                    {
                        addUpFloor(a);
                    }
                }
                else if(state.equals("MOVING_UP"))
                {
                    state="MOVING_DOWN";

                    for(Integer a: pendingRequest)
                    {
                        addDownFloor(a);
                    }
                }
            }
        }
    }

    public void pressedButton(int floor)
    {
        if(state.equals("MOVING_UP") && floor>currFloor)
        {
            addUpFloor(floor);
        }
        else if(state.equals("MOVING_DOWN") && floor<currFloor)
        {
            addDownFloor(floor);
        }
        else {

            pendingRequest.add(floor);
        }
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public int getElevatorID() {
        return elevatorID;
    }

    public ElevatorManager getManager() {
        return manager;
    }

    public void setManager(ElevatorManager manager) {
        this.manager = manager;
    }

    public List<Boolean> getFloorList() {
        return floorList;
    }

    public void setFloorList(List<Boolean> floorList) {
        this.floorList = floorList;
    }

    public List<Integer> getPendingRequest() {
        return pendingRequest;
    }

    public void setPendingRequest(List<Integer> pendingRequest) {
        this.pendingRequest = pendingRequest;
    }

    public int getFinalFloor() {
        return finalFloor;
    }

    public void setFinalFloor(int finalFloor) {
        this.finalFloor = finalFloor;
    }

    public int getCurrFloor() {
        return currFloor;
    }

    public void setCurrFloor(int currFloor) {
        this.currFloor = currFloor;
    }
}
