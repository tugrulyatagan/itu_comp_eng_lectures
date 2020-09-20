using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class User_Profile_Edit : UserBasePage
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
        tbName.Text = CurrentUser.Name;
        tbSurname.Text = CurrentUser.Surname;
        tbMail.Text = CurrentUser.Mail;
        tbUsername.Text = CurrentUser.Username;
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        CurrentUser.Name = tbName.Text.Trim();
        CurrentUser.Surname = tbSurname.Text.Trim();
        CurrentUser.Mail = tbMail.Text.Trim();
        if (tbNewPassword.Text.Trim() != "" && tbNewPasswordAgain.Text.Trim() != "")
        {
            if (tbNewPassword.Text.Trim() == tbNewPasswordAgain.Text.Trim())
            {
                CurrentUser.UpdatePassword(tbNewPassword.Text.Trim());
            }
            else
            {
                alert.AlertType = UserControlLibrary_ValidationAlert.AlertTypes.Error;
                alert.Alert("Passwords don't match!");
                return;
            }
        }
        else
        {
            alert.AlertType = UserControlLibrary_ValidationAlert.AlertTypes.Error;
            alert.Alert("Fill two boxes to change your password!");
            return;
        }

        Provider.SaveChanges();
        alert.AlertType = UserControlLibrary_ValidationAlert.AlertTypes.Success;
        alert.Alert("Information updated successfully!");
    }
}