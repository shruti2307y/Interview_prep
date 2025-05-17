import java.util.List;

public class ElevatorManager {

    private List<Elevator> elevatorList;

    private List<Integer> upPending;

    private List<Integer> downPending;

    public void requestUp(int source)
    {
        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("MOVING_UP") && e.getCurrFloor()<source)
            {
                e.addUpFloor(source);
                return;
            }
        }
        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("MOVING_DOWN_PICK"))
            {
                e.getFloorList().set(e.getFinalFloor(),false);
                e.getPendingRequest().add(e.getFinalFloor());
                e.setFinalFloor(source);
                return ;
            }
        }
        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("IDLE"))
            {
                if(e.getCurrFloor()>source)
                {
                    e.setState("MOVING_DOWN_PICK");
                    e.addDownFloor(source);
                }
                else {
                    e.setState("MOVING_UP");
                    e.addUpFloor(source);
                }
            }
        }

        upPending.add(source);
    }

    public void requestDown(int source)
    {
        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("MOVING_DOWN") && e.getCurrFloor()>source)
            {
                e.addDownFloor(source);
                return;
            }
        }

        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("MOVING_UP_PICK"))
            {
                e.getFloorList().set(e.getFinalFloor(),false);
                e.getPendingRequest().add(e.getFinalFloor());
                e.setFinalFloor(source);
                return ;
            }
        }

        for(Elevator e: elevatorList)
        {
            if(e.getState().equals("IDLE"))
            {
                if(e.getCurrFloor()>source)
                {
                    e.setState("MOVING_DOWN");
                    e.addDownFloor(source);
                }
                else {
                    e.setState("MOVING_UP_PICK");
                    e.addUpFloor(source);
                }
            }
        }

        downPending.add(source);
    }

    public void notifyIDLE(Elevator elevator) {
        if(!upPending.isEmpty()) {
            for (Integer src : upPending) {
                requestUp(src);
            }
            return;
        }
        if(!downPending.isEmpty())
        {
            for(Integer src: downPending)
            {
                requestDown(src);
            }
        }
    }


}
