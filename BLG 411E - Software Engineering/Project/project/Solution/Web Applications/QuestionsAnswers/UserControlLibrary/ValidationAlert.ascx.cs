using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class UserControlLibrary_ValidationAlert : System.Web.UI.UserControl
{
    public enum AlertTypes
    {
        Error = 1,
        Block = 2,
        Info = 3,
        Success = 4
    }
    public string Text { get; set; }
    public AlertTypes AlertType { get; set; }
    public string GetAlertType()
    {
        switch (AlertType)
        {
            case AlertTypes.Error:
                return "alert alert-error";
            case AlertTypes.Block:
                return "alert alert-block";
            case AlertTypes.Info:
                return "alert alert-info";
            case AlertTypes.Success:
                return "alert alert-success";
            default:
                return "alert alert-error";
        }
    }

    protected void Page_Init(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            Visible = false;
            ViewStateMode = System.Web.UI.ViewStateMode.Disabled;
        }
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        lbError.Text = Text;
    }

    public void Alert()
    {
        Visible = true;
    }

    public void Alert(string text)
    {
        Alert();
        lbError.Text = text;
    }
}