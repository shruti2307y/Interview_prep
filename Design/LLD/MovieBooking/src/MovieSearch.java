import java.util.List;

public interface MovieSearch {

    public List<Show> getShowByMovie(Movie movie);
    public List<Cinema> getCinemaByCity(City city);
    public List<Movie> getMoviesByCity(City city);

}
