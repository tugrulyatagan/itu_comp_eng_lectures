package wicket.quickstart;

import org.apache.wicket.markup.html.link.Link;

public class MovieDisplayPageLink extends Link {
    private Movie _movie;

    public MovieDisplayPageLink(String id, Movie movie) {
        super(id);
        this._movie = movie;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new MovieDisplayPage(this._movie));
    }
}
