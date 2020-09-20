<%@ Control Language="C#" AutoEventWireup="true" CodeFile="ValidationAlert.ascx.cs" Inherits="UserControlLibrary_ValidationAlert" %>

<div class="<%=GetAlertType() %>">
    <asp:Label ID="lbError" runat="server"></asp:Label>
</div>