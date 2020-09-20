using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class User_Profile_Default : BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        rpQuestion.DataSource = Provider.GetQuestionListByUserID(GivenUserID);
        rpQuestion.DataBind();
    }
}