package wicket.quickstart;

public class Movie {
    private Integer _id = null;
    private String _title = null;
    private Integer _year = null;

    public Movie() {
    }

    public void setId(Integer id) {
        this._id = id;
    }

    public Integer getId() {
        return this._id;
    }

    public Movie(String title) {
        this.setTitle(title);
    }

    public void setTitle(String title) {
        this._title = title;
    }

    public String getTitle() {
        return this._title;
    }

    public void setYear(Integer year) {
        this._year = year;
    }

    public Integer getYear() {
        return this._year;
    }
}
