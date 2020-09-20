package wicket.quickstart;

public class MovieListPage extends BasePage {
    public MovieListPage() {
        MovieListForm movieListForm = new MovieListForm("movie_list_form");
        this.add(movieListForm);
    }
}
