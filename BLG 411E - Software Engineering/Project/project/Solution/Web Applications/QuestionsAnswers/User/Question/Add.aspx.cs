using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Telerik.Web.UI;

public partial class User_Question_Add : UserBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            BindToPage();
        }
    }

    protected void BindToPage()
    {
        rcbTag.DataSource = Provider.GetTagList();
        rcbTag.DataBind();
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        Question question = Provider.AddQuestion(CurrentUser.ID, tbTitle.Text.Trim(), tbText.Text.Trim());
        foreach (RadComboBoxItem item in rcbTag.Items)
        {
            if (item.Checked)
            {
                QuestionTag questionTag = Provider.AddQuestionTag(question.ID, int.Parse(item.Value));
            }
        }

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA").Url);
    }
}