package wicket.quickstart;

import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.model.CompoundPropertyModel;

public class MovieEditForm extends Form {
    private boolean _newMovie;

    public MovieEditForm(String id, Movie movie, boolean newMovie) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(movie);
        this.setModel(model);

        this.add(new TextField("title"));
        this.add(new TextField("year"));

        this._newMovie = newMovie;
    }

    @Override
    public void onSubmit() {
        Movie movie = (Movie) this.getModelObject();
        WicketApplication app = (WicketApplication) this.getApplication();
        IMovieCollection collection = app.getCollection();
        if (this._newMovie)
            collection.addMovie(movie);
        else
            collection.updateMovie(movie);
        this.setResponsePage(new MovieDisplayPage(movie));
    }
}
