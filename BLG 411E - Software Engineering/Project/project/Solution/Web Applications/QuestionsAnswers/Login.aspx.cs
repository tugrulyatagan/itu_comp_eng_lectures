using Model;
using CodeLibrary.Navigation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Login : BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (CurrentUser != null)
        {
            Response.Redirect(new SiteMapLink("QA.Logout").Url);
        }
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        User user = Provider.GetUserByUsernameAndPassword(tbUsername.Text.Trim(), tbPassword.Text.Trim());
        if (user != null)
        {
            Session.Add("CurrentUser", user);
            Response.Redirect(new SiteMapLink("QA").Url);
        }
        else
        {
            alert.Alert("Username or password doesn't match!");
        }
    }
}