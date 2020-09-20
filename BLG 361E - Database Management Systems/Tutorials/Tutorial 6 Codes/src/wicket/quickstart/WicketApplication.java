package wicket.quickstart;

import java.io.File;

import org.apache.wicket.markup.html.WebPage;
import org.apache.wicket.protocol.http.WebApplication;

public class WicketApplication extends WebApplication {
    private IMovieCollection _collection;

    @Override
    public Class<? extends WebPage> getHomePage() {
        return HomePage.class;
    }

    @Override
    public void init() {
        super.init();

        String homeDir = System.getProperty("user.home");
        String dbFilePath = homeDir + File.separator + "movies.sqlite";
        this._collection = new MovieCollectionJDBC(dbFilePath);
    }

    public IMovieCollection getCollection() {
        return this._collection;
    }
}
