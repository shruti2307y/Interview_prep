

## Requirements

* We need a movie ticket booking system.
* List out all the cinema hall within a city
* List of out all the show within a cinema hall for a particular movie
* List out all the movies running in a cinema hall
* List of all the movies available in a city.
* Book shows with multiple seats

## Asking right Questions

* Movies Genres ?
* List out top selling movies, hot movies or any priority list ?
* Seat types? and in future will we have more ?
* Variable pricing ? or fixed pricing ?
* Multiple seats per booking ?


## The actual Code

### The BookingSystemClass
```java
class BookingSystemClass
{
	private Map<String,List<Cinema>> cinemaList;
	private List<Movie> movieList;
	private Map<String,List<Movie>> movieListPerCity;

	public List<Cinema> getCinemasBasedOnCity(String city)
	{
		return cinemaList.get(city);
	}

	public Booking makeBooking(User user, Show show, List<ShowSeat> showSeats)
	{
		try{

			Booking booking = show.bookSeats(showSeats, user);
			Payment payment = user.makePayment(Booking booking);

			if(payment.status == PaymentStatus.FAILED)
			{
				// rollback
			}

		}catch(BookingNotAllowed e)
		{
			
		}
	}
}

class Cinema {

	private String city;
	private String cinemaName;
	private Address address;
	
	private List<CinemaHall> cinemaHallList;
	private Map<Movie,List<Show>> showList;

	public List<Show> getShows( Movie movie)
	{
		return showList.get(movie);
	}
	public List<Movie> getMovieList(){

		return showList.keyset();
	}
}

class CinemaHall
{
	private int cinemaHallId;
}

class Show {
    private Timestamp showTiming;
    private String showDescription;
    private int showId;
    private Movie movie;
    private List<ShowSeat> seats;

    public List<ShowSeat> getAllSeats() {
        return seats;
    }

    @Transactional
    public synchronized Booking bookSeats(List<ShowSeat> requestedSeats, User user) throws BookingNotAllowed {
        List<ShowSeat> successfullyBookedSeats = new ArrayList<>();
        try {
            for (ShowSeat seat : requestedSeats) {
                if (seat.isBooked()) {
                    throw new BookingNotAllowed("Seat " + seat.getName() + " is already booked.");
                }
                seat.setBooked();  // Reserve the seat
                successfullyBookedSeats.add(seat);
            }
            // Create booking object
            return new Booking(this, successfullyBookedSeats, user);
        } catch (BookingNotAllowed e) {
            // Rollback previously booked seats
            successfullyBookedSeats.forEach(seat -> seat.setAvailable());
            throw e; // Rethrow exception for upper layers to handle
        }
    }
}


interface PricingStrategy {
    double calculatePrice(ShowSeat seat, Show show);
}

class RegularPricingStrategy implements PricingStrategy {
    @Override
    public double calculatePrice(ShowSeat seat, Show show) {
        return seat.getBaseCost();  // Fixed price based on seat cost
    }
}

class DynamicPricingStrategy implements PricingStrategy {
    @Override
    public double calculatePrice(ShowSeat seat, Show show) {
        double basePrice = seat.getBaseCost();
        if (show.getShowTiming().getDayOfWeek() == DayOfWeek.SATURDAY || show.getShowTiming().getDayOfWeek() == DayOfWeek.SUNDAY) {
            return basePrice * 1.2;  // 20% increase on weekends
        }
        return basePrice;
    }
}

class Booking {
    private Show show;
    private Timestamp bookingTime;
    private List<ShowSeat> bookedSeats;
    private double totalAmount;
    private PaymentStatus paymentStatus;
    private Payment payment;
    private User user;

    public Booking(Show show, List<ShowSeat> bookedSeats, User user) {
        this.show = show;
        this.bookedSeats = bookedSeats;
        this.user = user;
        this.paymentStatus = PaymentStatus.PENDING;
        this.totalAmount = calculateTotalAmount(show, bookedSeats);
    }

    private double calculateTotalAmount(Show show, List<ShowSeat> bookedSeats) {
        PricingStrategy pricingStrategy = getPricingStrategy(show);  // Determine pricing strategy
        return bookedSeats.stream().mapToDouble(seat -> pricingStrategy.calculatePrice(seat, show)).sum();
    }

    private PricingStrategy getPricingStrategy(Show show) {
        // Placeholder logic: dynamic pricing for weekends, regular pricing otherwise
        DayOfWeek dayOfWeek = show.getShowTiming().toLocalDateTime().getDayOfWeek();
        return (dayOfWeek == DayOfWeek.SATURDAY || dayOfWeek == DayOfWeek.SUNDAY) ? new DynamicPricingStrategy() : new RegularPricingStrategy();
    }

    public void markPaymentDone() {
        this.paymentStatus = PaymentStatus.DONE;
    }

    public void markPaymentFailed() {
        this.paymentStatus = PaymentStatus.FAILED;
    }
}


public Payment{

	private Timestamp paymentTime;
	private int transactionId;
	private PaymentMode paymentMode;
	private PaymentStatus status;

	public Payment(PaymentMode paymentMode)
	{
		this.paymentMode = paymentMode;
		this.status = PaymentStatus.PENDING;
	}

	public PaymentStatus makePayment(User user, double amount)
	{
		Boolean paymentDone = //

		if(paymentDon)
		{
			this.status = PaymentStatus.DONE;
			
		}
		else
		{
			this.status = PaymentStatus.FAILED;
		}
		return this.status;
	}
}
public User {

	private String userId;
	private String emailId;
	private String userName;
	private PayemntMode paymentMode;

	public makePayment(Booking booking)
	{
		Payment payment = new Payment(this.paymentMode);
		payment.makePayment(this,booking.getAmount());

		booking.setPayment(payment);
		return payment;
	}
}

class ShowSeat{

	private String seatId;
	private int seatRow;
	private int seatColumn;
	private SeatType seatType;
	private Boolean reserved;
	private Double seatCost;
}

enum SeatType{

	REGULAR,
	SPECIAL
}

enum PaymentStatus
{
	PENDING,
	DONE,
	FAILED
}
```