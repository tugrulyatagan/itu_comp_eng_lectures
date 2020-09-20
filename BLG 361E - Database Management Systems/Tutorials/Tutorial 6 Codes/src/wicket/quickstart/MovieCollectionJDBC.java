package wicket.quickstart;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;

public class MovieCollectionJDBC implements IMovieCollection {
    private Connection _db;

    public MovieCollectionJDBC(String dbFilePath) {
        try {
            Class.forName("org.sqlite.JDBC");
        } catch (ClassNotFoundException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }

        try {
            String jdbcURL = "jdbc:sqlite:" + dbFilePath;
            this._db = DriverManager.getConnection(jdbcURL);
        } catch (SQLException ex) {
            throw new UnsupportedOperationException(ex.getMessage());
        }
    }

    public List<Movie> getMovies() {
        List<Movie> movies = new LinkedList<Movie>();
        try {
            String query = "SELECT ID, TITLE, YEAR FROM MOVIE";
            Statement statement = this._db.createStatement();
            ResultSet results = statement.executeQuery(query);
            while (results.next()) {
                Integer id = results.getInt("ID");
                String title = results.getString("TITLE");
                Integer year = results.getInt("YEAR");
                Movie movie = new Movie(title);
                movie.setId(id);
                movie.setYear(year);
                movies.add(movie);
            }
            results.close();
            statement.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
        return movies;
    }

    public void addMovie(Movie movie) {
        try {
            String query = "INSERT INTO MOVIE (TITLE, YEAR) VALUES (?, ?)";
            PreparedStatement statement = this._db.prepareStatement(query);
            statement.setString(1, movie.getTitle());
            statement.setInt(2, movie.getYear());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }

    public void deleteMovie(Movie movie) {
        try {
            String query = "DELETE FROM MOVIE WHERE (ID = ?)";
            PreparedStatement statement = this._db.prepareStatement(query);
            statement.setInt(1, movie.getId());
            statement.executeUpdate();
            statement.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }

    public void updateMovie(Movie movie) {
        try {
            String query = "UPDATE MOVIE SET TITLE = ?, YEAR = ? WHERE (ID = ?)";
            PreparedStatement statement = this._db.prepareStatement(query);
            statement.setString(1, movie.getTitle());
            statement.setInt(2, movie.getYear());
            statement.setInt(3, movie.getId());
            statement.executeUpdate();
            statement.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }
}
