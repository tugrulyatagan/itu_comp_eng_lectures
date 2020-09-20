package wicket.quickstart;

public final class MovieEditPage extends BasePage {
    public MovieEditPage(Movie movie) {
        this.add(new MovieEditForm("movie_edit", movie, true));
    }

    public MovieEditPage(Movie movie, boolean newMovie) {
        this.add(new MovieEditForm("movie_edit", movie, newMovie));
    }
}
