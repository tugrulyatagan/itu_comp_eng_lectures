using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CodeLibrary.Navigation;

public partial class _Default : BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            BindToPage();
        }

        NavigationHeader header = null;
        if (CurrentUser != null)
        {
            header = new NavigationHeader(Setting.NavigationHeader.DefaultHeader);
            header.AddLink(new SiteMapLink("QA.User.Question.Add"));
            header.AddLink(new SiteMapLink("QA.User"));
            Navigation.AddHeader(header);

            if (CurrentUser.UserTypeID == (int)UserType.Admin)
            {
                header.AddLink(new SiteMapLink("QA.Admin.Tag"));
                header.AddLink(new SiteMapLink("QA.Admin.Badge"));
            }
        }
    }

    protected void BindToFavoriteTag()
    {
        rpFavoriteTag.DataSource = Provider.GetUserTagListByUserTagTypeAndUserID(UserTagType.FavoriteTag, CurrentUser.ID);
        rpFavoriteTag.DataBind();
    }

    protected void BindToPage()
    {
        List<Model.Question> questionList = Provider.GetQuestionList();

        rpQuestion.DataSource = questionList;
        rpQuestion.DataBind();

        if (CurrentUser != null)
        {
            pnUserSpecific.Visible = true;

            List<Tag> favoriteTagList = Provider.GetUserTagListByUserTagTypeAndUserID(UserTagType.FavoriteTag, CurrentUser.ID).Select(o => o.Tag).ToList();
            List<Model.Question> interestingQuestionList = new List<Model.Question>();
            foreach (Model.Question question in questionList)
            {
                List<Tag> tagList = Provider.GetQuestionTagListByQuestionID(question.ID).Select(o => o.Tag).ToList();
                if (tagList.Intersect(favoriteTagList).Count() > 0)
                {
                    interestingQuestionList.Add(question);
                }
            }

            rpInterestingQuestion.DataSource = interestingQuestionList;
            rpInterestingQuestion.DataBind();

            BindToFavoriteTag();
        }
    }

    protected void rpFavoriteTag_ItemCommand(object sender, RepeaterCommandEventArgs e)
    {
        if (e.CommandName == "Delete")
        {
            HiddenField hfFavoriteTagID = e.Item.FindControl("hfFavoriteTagID") as HiddenField;
            UserTag favoriteTag = Provider.GetUserTagByID(new Guid(hfFavoriteTagID.Value));
            favoriteTag.Delete();
            Provider.SaveChanges();
        }

        if (e.CommandName == "Add")
        {
            DropDownList ddlTag = e.Item.FindControl("ddlTag") as DropDownList;
            UserTag favoriteTag = Provider.AddUserTag(UserTagType.FavoriteTag, int.Parse(ddlTag.SelectedValue), CurrentUser.ID);
            Provider.SaveChanges();
        }

        BindToFavoriteTag();
    }
    protected void rpFavoriteTag_ItemDataBound(object sender, RepeaterItemEventArgs e)
    {
        if (e.Item.ItemType == ListItemType.Footer)
        {
            DropDownList ddlTag = e.Item.FindControl("ddlTag") as DropDownList;
            List<Tag> favoriteTags = Provider.GetUserTagListByUserTagTypeAndUserID(UserTagType.FavoriteTag, CurrentUser.ID).Select(o => o.Tag).ToList();
            List<Tag> allTags = Provider.GetTagList();

            ddlTag.DataSource = allTags.Except(favoriteTags);
            ddlTag.SelectedIndex = 0;
            ddlTag.DataBind();
        }
    }
}