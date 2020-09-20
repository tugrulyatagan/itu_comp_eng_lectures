<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="Admin_Badge_Default" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div class="span6">
        <asp:Repeater ID="rpBadge" runat="server">
            <HeaderTemplate>
                <table class="table table-hover">
                    <thead>
                        <tr>
                            <th></th>
                            <th>Name</th>
                            <th>Information Text</th>
                        </tr>
                    </thead>
                    <tbody>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%# new SiteMapLink("QA.Admin.Badge.Edit") { Icon = "icon-edit" }.AddQueryString(Setting.QueryString.Badge, Eval("ID").ToString()).PrintIcon() %>
                        <%# new SiteMapLink("QA.Admin.Badge.Delete") { Icon = "icon-remove" }.AddQueryString(Setting.QueryString.Badge, Eval("ID").ToString()).PrintIcon() %>
                    </td>
                    <td><%# Eval("Name") %></td>
                    <td><%# Eval("InformationText") %></td>
                </tr>
            </ItemTemplate>
            <FooterTemplate>
                </tbody>
            </table>
            </FooterTemplate>
        </asp:Repeater>
    </div>
</asp:Content>

