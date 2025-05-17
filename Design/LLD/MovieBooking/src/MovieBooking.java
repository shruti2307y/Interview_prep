import java.sql.Time;
import java.util.List;

public class MovieBooking {

    private Show show;
    private List<ShowSeat> bookedSeats;
    private String bookingStatus;
    private Time bookingTime;

    private Payment payment;

    public void cancelBooking(){};
    public void refund(){};
}
