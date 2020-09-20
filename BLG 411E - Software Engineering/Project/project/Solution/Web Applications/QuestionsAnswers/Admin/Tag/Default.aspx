<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="Admin_Tag_Default" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div class="span6">
        <asp:Repeater ID="rpTag" runat="server">
            <HeaderTemplate>
                <table class="table table-hover">
                    <thead>
                        <tr>
                            <th></th>
                            <th>Name</th>
                            <th>InformationText</th>
                        </tr>
                    </thead>
                    <tbody>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%# new SiteMapLink("QA.Admin.Tag.Edit") { Icon = "icon-edit" }.AddQueryString(Setting.QueryString.Tag, Eval("ID").ToString()).PrintIcon() %>
                        <%# new SiteMapLink("QA.Admin.Tag.Delete") { Icon = "icon-remove" }.AddQueryString(Setting.QueryString.Tag, Eval("ID").ToString()).PrintIcon() %>
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

