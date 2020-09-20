package wicket.quickstart;

import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.link.Link;

public class MovieDisplayPage extends BasePage {
    private Movie _movie;

    public MovieDisplayPage(Movie movie) {
        this._movie = movie;

        this.add(new Label("title", movie.getTitle()));
        this.add(new Label("year", movie.getYear().toString()));

        Link editLink = new Link("edit_link") {
            @Override
            public void onClick() {
                MovieDisplayPage parent = (MovieDisplayPage) this.getParent();
                this.setResponsePage(new MovieEditPage(parent.getMovie(), false));
            }
        };
        this.add(editLink);
    }

    public Movie getMovie() {
        return this._movie;
    }
}
