<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Add.aspx.cs" Inherits="User_Question_Add" %>

<%@ Register TagPrefix="telerik" Namespace="Telerik.Web.UI" Assembly="Telerik.Web.UI" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
    <div class="alert alert-warning">
        <strong>Please!</strong>
        <p>follow the rules in your questions. Homework questions are not allowed.</p>
    </div>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div>
        <p>* required.</p>
        <div class="control-group">
            <label class="control-label">Title *</label>
            <div class="controls">
                <asp:TextBox ID="tbTitle" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="tbTitle" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Text *</label>
            <div class="controls">
                <asp:TextBox ID="tbText" TextMode="MultiLine" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="tbText" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Question Tags</label>
            <div class="controls">
                <telerik:RadComboBox ID="rcbTag" CheckBoxes="true" DataTextField="Name" EmptyMessage="Select" DataTextFormatString=" {0}" DataValueField="ID" runat="server">
                </telerik:RadComboBox>
            </div>
        </div>

        <div class="control-group">
            <div class="controls">
                <asp:LinkButton ID="lbtSubmit" OnClick="lbtSubmit_Click" Text="Submit" CssClass="btn btn-success" ValidationGroup="Submit" runat="server"></asp:LinkButton>
            </div>
        </div>
    </div>
</asp:Content>

