using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class AdminMasterPage : BaseMasterPage
{
    public int LeftSpanLength = 3;

    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            BindToMasterPage();
        }
    }

    protected void Page_PreRender(object sender, EventArgs e)
    {
        BindToLeft();
    }

    protected void BindToMasterPage()
    {
        BindToBreadcrumb();
    }

    protected void BindToBreadcrumb()
    {
        SiteMapNode cursorNode = SiteMap.Provider.CurrentNode;
        List<SiteMapNode> nodeList = new List<SiteMapNode>();

        while (cursorNode != null)
        {
            nodeList.Add(cursorNode);
            cursorNode = cursorNode.ParentNode;
        }

        rpBreadcrumb.DataSource = nodeList.Reverse<SiteMapNode>();
        rpBreadcrumb.DataBind();

        // Navigasyonun sonuncu elemanı için diğer paneli aktifleştirelim
        // Böylece son eleman seçili görünece.
        RepeaterItem lastItem = rpBreadcrumb.Items[rpBreadcrumb.Items.Count - 1];
        PlaceHolder phActiveBreadcrumb = lastItem.FindControl("phActiveBreadcrumb") as PlaceHolder;
        PlaceHolder phUnactiveBreadcrumb = lastItem.FindControl("phUnactiveBreadcrumb") as PlaceHolder;
        phActiveBreadcrumb.Visible = true;
        phUnactiveBreadcrumb.Visible = false;
    }

    protected void BindToLeft()
    {
        // Eğer Navigasyon'a bir şey eklenmemişse görünmesin.
        if ((Page as BasePage).Navigation.IsEmpty())
            pnLeftNavigation.Visible = false;

        // Eğer chpLeft ContentPlaceHolder'ı override edilmemişse görünmesin.
        if (!cphLeft.HasControls())
            pnLeftCPH.Visible = false;

        // Eğer hiç biri görünmüyorsa sol taraf hiç görünmesin.
        pnLeft.Visible = pnLeftNavigation.Visible || pnLeftCPH.Visible;
        if (!pnLeft.Visible)
            LeftSpanLength = 0;
    }
}