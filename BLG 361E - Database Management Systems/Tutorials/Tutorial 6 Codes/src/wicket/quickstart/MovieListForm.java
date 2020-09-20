package wicket.quickstart;

import java.util.LinkedList;
import java.util.List;

import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.form.Check;
import org.apache.wicket.markup.html.form.CheckGroup;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.PropertyListView;

public class MovieListForm extends Form {
    private List<Movie> _selectedMovies;

    public MovieListForm(String id) {
        super(id);
        this._selectedMovies = new LinkedList<Movie>();

        CheckGroup movieCheckGroup =
                new CheckGroup("selected_movies", this._selectedMovies);
        this.add(movieCheckGroup);

        WicketApplication app = (WicketApplication) this.getApplication();
        IMovieCollection collection = app.getCollection();
        List<Movie> movies = collection.getMovies();

        PropertyListView movieListView =
                new PropertyListView("movie_list", movies) {
            @Override
            protected void populateItem(ListItem item) {
                Movie movie = (Movie) item.getModelObject();
                MovieDisplayPageLink movieLink =
                        new MovieDisplayPageLink("movie_link", movie);
                movieLink.add(new Label("title"));
                movieLink.add(new Label("year"));
                item.add(new Check("selected", item.getModel()));
                item.add(movieLink);
            }
        };
        movieCheckGroup.add(movieListView);
    }

    @Override
    public void onSubmit() {
        WicketApplication app = (WicketApplication) this.getApplication();
        IMovieCollection collection = app.getCollection();
        for (Movie movie : this._selectedMovies)
            collection.deleteMovie(movie);
        this.setResponsePage(new MovieListPage());
    }
}
