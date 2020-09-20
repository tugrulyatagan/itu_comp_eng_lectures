using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class User_Profile_Add : BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        User user = Provider.AddUser(UserType.User, tbName.Text.Trim(), tbSurname.Text.Trim(), tbMail.Text.Trim(), tbUsername.Text.Trim(), "");
        if (tbNewPassword.Text.Trim() != "" && tbNewPasswordAgain.Text.Trim() != "")
        {
            if (tbNewPassword.Text.Trim() == tbNewPasswordAgain.Text.Trim())
            {
                user.UpdatePassword(tbNewPassword.Text.Trim());
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
        alert.Alert("Your account is created!");
    }
}