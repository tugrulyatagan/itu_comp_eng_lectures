using CodeLibrary.Navigation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Model;

public class BasePage : System.Web.UI.Page
{
    private Navigation FieldNavigation;
    public Navigation Navigation
    {
        get
		{
			if(FieldNavigation == default(Navigation))
			{
				FieldNavigation = new Navigation();
			}
			return FieldNavigation;
		}
    }

    private Entities FieldProvider;
    public Entities Provider
    {
        get
		{
			if(FieldProvider == default(Entities))
			{
                FieldProvider = new Entities();
			}
			return FieldProvider;
		}
    }

    #region QueryString Parameters
    private int FieldCurrentBadgeID;
    public int CurrentBadgeID
    {
        get
        {
            if (FieldCurrentBadgeID == 0)
            {
                if (Request.QueryString[Setting.QueryString.Badge] != null)
                    int.TryParse(Request.QueryString[Setting.QueryString.Badge].Trim(), out FieldCurrentBadgeID);
            }
            return FieldCurrentBadgeID;
        }
    }

    private int FieldCurrentTagID;
    public int CurrentTagID
    {
        get
        {
            if (FieldCurrentTagID == 0)
            {
                if (Request.QueryString[Setting.QueryString.Tag] != null)
                    int.TryParse(Request.QueryString[Setting.QueryString.Tag].Trim(), out FieldCurrentTagID);
            }
            return FieldCurrentTagID;
        }
    }

    private System.Guid FieldCurrentQuestionID;
    public System.Guid CurrentQuestionID
    {
        get
        {
            if (FieldCurrentQuestionID == System.Guid.Empty)
            {
                try { FieldCurrentQuestionID = new System.Guid(Request.QueryString[Setting.QueryString.Question].Trim()); }
                catch { }
            }
            return FieldCurrentQuestionID;
        }
    }

    private System.Guid FieldGivenUserID;
    public System.Guid GivenUserID
    {
        get
        {
            if (FieldGivenUserID == System.Guid.Empty)
            {
                try { FieldGivenUserID = new System.Guid(Request.QueryString[Setting.QueryString.User].Trim()); }
                catch { }
            }
            return FieldGivenUserID;
        }
    }
    #endregion

    #region Page Objects
    private User FieldCurrentUser;
    public User CurrentUser
    {
        get
		{
			if(FieldCurrentUser == default(User))
			{
                FieldCurrentUser = Session["CurrentUser"] as User;
			}
			return FieldCurrentUser;
		}
    }

    private Badge FieldCurrentBadge;
    public Badge CurrentBadge
    {
        get
        {
            if (FieldCurrentBadge == default(Badge))
            {
                FieldCurrentBadge = Provider.GetBadgeByID(CurrentBadgeID);
            }
            return FieldCurrentBadge;
        }
    }

    private Tag FieldCurrentTag;
    public Tag CurrentTag
    {
        get
        {
            if (FieldCurrentTag == default(Tag))
            {
                FieldCurrentTag = Provider.GetTagByID(CurrentTagID);
            }
            return FieldCurrentTag;
        }
    }

    private Question FieldCurrentQuestion;
    public Question CurrentQuestion
    {
        get
		{
			if(FieldCurrentQuestion == default(Question))
			{
                FieldCurrentQuestion = Provider.GetQuestionByID(CurrentQuestionID);
			}
			return FieldCurrentQuestion;
		}
    }

    private User FieldGivenUser;
    public User GivenUser
    {
        get
		{
			if(FieldGivenUser == default(User))
			{
                FieldGivenUser = Provider.GetUserByID(GivenUserID);
			}
			return FieldGivenUser;
		}
    }
    #endregion

    public BasePage()
	{
        this.PreInit += new EventHandler(BasePage_PreInit);
    }

    public virtual void BasePage_PreInit(object sender, EventArgs e)
    {

    }
}