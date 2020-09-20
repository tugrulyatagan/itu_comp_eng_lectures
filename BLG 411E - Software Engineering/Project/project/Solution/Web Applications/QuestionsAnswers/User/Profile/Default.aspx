<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="User_Profile_Default" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
        <ul class="nav nav-tabs" id="myTab">
        <li class="active"><a href="#questions">Questions</a></li>
        <li><a href="#interesting">Answers</a></li>
        <li><a href="#interesting">Comments</a></li>
        <li><a href="#interesting">Favorite Tags</a></li>
    </ul>
     
    <div class="tab-content">
        <div class="tab-pane active" id="questions">
        <asp:Repeater ID="rpQuestion" runat="server">
            <HeaderTemplate>
                <table class="table table-hover">
                    <thead>
                        <tr>
                            <th></th>
                            <th>Title</th>
                            <th>Text</th>
                        </tr>
                    </thead>
                    <tbody>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%# new SiteMapLink("QA.Admin.Question") { Icon = "glyphicon glyphicon-align-justify" }.AddQueryString(Setting.QueryString.Question, Eval("ID").ToString()).PrintIcon() %>
                    </td>
                    <td><%# Eval("Title") %></td>
                    <td><%# Eval("Text") %></td>
                </tr>
            </ItemTemplate>
            <FooterTemplate>
                </tbody>
            </table>
            </FooterTemplate>
        </asp:Repeater>
        </div>
    </div>
     
    <script>
        $('#myTab a').click(function (e) {
            e.preventDefault();
            $(this).tab('show');
        })
    </script>
</asp:Content>