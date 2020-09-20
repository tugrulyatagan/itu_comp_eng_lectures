package wicket.quickstart;

import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.panel.Panel;

public class NavigationPanel extends Panel {
    public NavigationPanel(String id) {
        super(id);

        Link homePageLink = new Link("home") {
            @Override
            public void onClick() {
                this.setResponsePage(new HomePage());
            }
        };
        this.add(homePageLink);

        Link movieListPageLink = new Link("list_movies") {
            @Override
            public void onClick() {
                this.setResponsePage(new MovieListPage());
            }
        };
        this.add(movieListPageLink);

        Link movieAddLink = new Link("add_movie") {
            @Override
            public void onClick() {
                Movie movie = new Movie();
                this.setResponsePage(new MovieEditPage(movie));
            }
        };
        this.add(movieAddLink);
    }
}
