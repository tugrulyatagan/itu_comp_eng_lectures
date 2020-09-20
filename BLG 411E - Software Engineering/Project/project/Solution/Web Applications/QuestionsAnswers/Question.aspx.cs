using CodeLibrary.Navigation;
using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Question : BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            BindToPage();
        }
    }

    protected void BindToQuestionComment()
    {
        rpComment.DataSource = Provider.GetQuestionCommentListByQuestionID(CurrentQuestionID).OrderBy(o => o.CreateDate);
        rpComment.DataBind();
    }

    protected void BindToAnswer()
    {
        rpAnswer.DataSource = Provider.GetAnswerListByQuestionID(CurrentQuestionID);
        rpAnswer.DataBind();
    }

    protected void BindToPage()
    {
        rpTag.DataSource = Provider.GetQuestionTagListByQuestionID(CurrentQuestionID);
        rpTag.DataBind();

        BindToQuestionComment();
        BindToAnswer();
    }

    protected void lbtAddComment_Click(object sender, EventArgs e)
    {
        pnQuestionComment.Visible = true;
        pnAddQuestionComment.Visible = false;
    }

    protected void lbtAddAnswer_Click(object sender, EventArgs e)
    {
        Answer answer = Provider.AddAnswer(CurrentUser.ID, CurrentQuestionID, tbAnswer.Text.Trim());
        Provider.SaveChanges();

        BindToAnswer();
    }

    protected void lbtSaveComment_Click(object sender, EventArgs e)
    {
        Comment questionComment = Provider.AddQuestionComment(CurrentQuestionID, tbComment.Text.Trim(), CurrentUser.ID);
        Provider.SaveChanges();
        BindToQuestionComment();

        pnQuestionComment.Visible = false;
        pnAddQuestionComment.Visible = true;
    }

    protected void lbtCancelComment_Click(object sender, EventArgs e)
    {
        pnQuestionComment.Visible = false;
        pnAddQuestionComment.Visible = true;
    }
}