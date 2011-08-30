<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet 
  version="1.0" 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
>

<xsl:output
  omit-xml-declaration="yes"
  method="xml"
  indent="yes"
/>

<xsl:template match="@*|node()|text()|comment()|processing-instruction()">
  <xsl:copy>
    <xsl:apply-templates select="@*|node()|text()|comment()|processing-instruction()" />
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>
