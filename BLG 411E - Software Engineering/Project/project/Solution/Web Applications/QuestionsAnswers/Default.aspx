<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
<asp:Panel ID="pnUserSpecific" Visible="false" runat="server">
    <div class="alert alert-success">
        <strong>Favorite Tags</strong>
        <p>
            <asp:Repeater ID="rpFavoriteTag" OnItemCommand="rpFavoriteTag_ItemCommand" OnItemDataBound="rpFavoriteTag_ItemDataBound" runat="server">
                <HeaderTemplate>
                    <ul class="list-unstyled">
                </HeaderTemplate>
                <ItemTemplate>
                    <li>
                        <%# Eval("Tag.Name") %>
                        <asp:HiddenField ID="hfFavoriteTagID" Value='<%# Eval("ID") %>' runat="server" />
                        <asp:LinkButton ID="lbtDeleteFavoriteTag" CommandName="Delete" CssClass="icon icon-remove" runat="server"></asp:LinkButton>
                    </li>
                </ItemTemplate>
                <FooterTemplate>
                    </ul>
                    <div class="control-group">
                        <div class="controls">
                            <asp:DropDownList ID="ddlTag" DataTextField="Name" DataValueField="ID" Width="180" runat="server"></asp:DropDownList>
                            <asp:LinkButton ID="lbtAddTag" CommandName="Add" Text="Add " CssClass="btn btn-success" runat="server"></asp:LinkButton>
                        </div>
                    </div>
                </FooterTemplate> 
            </asp:Repeater>
        </p>
    </div>
</asp:Panel>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <ul class="nav nav-tabs" id="myTab">
        <li class="active"><a href="#questions">Questions</a></li>
        <li><a href="#interesting">Interesting Questions</a></li>
    </ul>
     
    <div class="tab-content">
        <div class="tab-pane active" id="questions">
            <asp:Repeater ID="rpQuestion" runat="server">
                <HeaderTemplate>
                </HeaderTemplate>
                <ItemTemplate>
                    <div class="well">
                        <p><b><%# new SiteMapLink("QA.Question").AddQueryString(Setting.QueryString.Question, Eval("ID").ToString()).ToString(Eval("Title").ToString()) %></b></p>
                        <p><%# Eval("Text") %></p>
                        <p><%# Eval("User.Name") %> <%# Eval("User.Surname") %></p>
                    </div>
                </ItemTemplate>
                <FooterTemplate>
                </FooterTemplate>
            </asp:Repeater>
        </div>
        <div class="tab-pane" id="interesting">
            <asp:Repeater ID="rpInterestingQuestion" runat="server">
                <HeaderTemplate>
                </HeaderTemplate>
                <ItemTemplate>
                    <div class="well">
                        <p><b><%# new SiteMapLink("QA.Question").AddQueryString(Setting.QueryString.Question, Eval("ID").ToString()).ToString(Eval("Title").ToString()) %></b></p>
                        <p><%# Eval("Text") %></p>
                        <p><%# Eval("User.Name") %> <%# Eval("User.Surname") %></p>
                    </div>
                </ItemTemplate>
                <FooterTemplate>
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

