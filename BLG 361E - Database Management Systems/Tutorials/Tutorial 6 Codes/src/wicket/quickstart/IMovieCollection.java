package wicket.quickstart;

import java.util.List;

public interface IMovieCollection {
    public List<Movie> getMovies();
    public void addMovie(Movie movie);
    public void deleteMovie(Movie movie);
    public void updateMovie(Movie movie);
}
