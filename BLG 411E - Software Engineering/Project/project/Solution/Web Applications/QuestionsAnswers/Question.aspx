<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Question.aspx.cs" Inherits="Question" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div class="well">
        <h2><%= CurrentQuestion.Title %></h2>
        <p><%= CurrentQuestion.Text %></p>
        <p>
            Tags: 
            <asp:Repeater ID="rpTag" runat="server">
                <ItemTemplate>
                    <%# Eval("Tag.Name") %>
                </ItemTemplate>
                <SeparatorTemplate> | </SeparatorTemplate>
            </asp:Repeater>
        </p>
        <p><%= CurrentQuestion.User.Name + " " + CurrentQuestion.User.Surname %></p>

        <asp:Panel ID="pnAddQuestionComment" runat="server">
            <div class="control-group">
                <div class="controls">
                    <asp:LinkButton ID="lbtAddComment" OnClick="lbtAddComment_Click" Text="Add Comment" CssClass="btn btn-success" runat="server"></asp:LinkButton>
                </div>
            </div>
        </asp:Panel>

        <asp:Panel ID="pnQuestionComment" Visible="false" runat="server">
            <div class="control-group">
                <label class="control-label">Your comment: </label>
                <div class="controls">
                    <asp:TextBox ID="tbComment" TextMode="MultiLine" runat="server"></asp:TextBox>
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="tbComment" ValidationGroup="AddComment" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
                    <br />
                    <asp:LinkButton ID="lbtSaveComment" OnClick="lbtSaveComment_Click" Text="Save" CssClass="btn btn-success" runat="server"></asp:LinkButton>
                    <asp:LinkButton ID="lbtCancelComment" OnClick="lbtCancelComment_Click" Text="Cancel" CssClass="btn btn-default" runat="server"></asp:LinkButton>
                </div>
            </div>
        </asp:Panel>

        <asp:Repeater ID="rpComment" runat="server">
            <ItemTemplate>
                <p>
                    Comment: <%# Eval("Text") %> - <%# Eval("User.Name") %> <%# Eval("User.Surname") %> @ <%# Eval("CreateDate") %>
                </p>
            </ItemTemplate>
        </asp:Repeater>
    </div>

    <h2>Answers</h2>    
    <asp:Repeater ID="rpAnswer" runat="server">
        <ItemTemplate>
            <div class="well">
                <%# Eval("Text") %>
                <br />
                <%# Eval("User.Name") %> <%# Eval("User.Surname") %> @ <%# Eval("CreateDate") %>
            </div>
        </ItemTemplate>
    </asp:Repeater>

    <div class="control-group">
        <label class="control-label">Your answer: </label>
        <div class="controls">
            <asp:TextBox ID="tbAnswer" TextMode="MultiLine" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="tbAnswer" ValidationGroup="AddAnswer" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            <br />
            <asp:LinkButton ID="lbtAddAnswer" OnClick="lbtAddAnswer_Click" ValidationGroup="AddAnswer" Text="Post Your Answer" CssClass="btn btn-success" runat="server"></asp:LinkButton>
        </div>
    </div>

</asp:Content>

