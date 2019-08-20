// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 07/18/2019 at 1:13pm by CFranklin
//
// *****************************************************************************

#include "JHP_Utilities.h"



API_OverrideRule SetRuleStyleToRed(API_OverrideRule rule)
{
	BNZeroMemory(&rule.style, sizeof(API_OverrideRuleStyle));
	rule.style.lineMarkerTextPen.attributeIndex = 122;
	rule.style.lineMarkerTextPen.overridden = true;
	rule.style.overridePenColorAndThickness = false;
	rule.style.showSkinSeparators = false;

	return rule;
}

API_OverrideRule JHP_WallAngleRule(API_Guid guid = APINULLGuid)
{
	API_OverrideRule rule = { guid, "API_AUDIT_Wall Angle"};
	rule.criterionXML =
		"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
		"<CriterionExpression Mv=\"2\" Sv=\"1\">"
		"			<TextMatchType>1</TextMatchType>"
		"			<Size>1</Size>"
		"			<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"			<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"				<LogicalOperator>2</LogicalOperator>"
		"				<CriteriaCount>4</CriteriaCount>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>B4B7B134-EC56-4D40-8D4C-71D7C5A2493A</ClassGuid>"
		"					<ElemTypeCriterion Mv=\"2\" Sv=\"3\">"
		"						<VBEF::CritToolType Mv=\"1\" Sv=\"0\">"
		"							<ElemRegistryRefId>1463897138</ElemRegistryRefId>"
		"							<ElemCreatorToolUnID>"
		"								<MainGuid>00000000-0000-0000-0000-000000000000</MainGuid>"
		"								<RevGuid>00000000-0000-0000-0000-000000000000</RevGuid>"
		"							</ElemCreatorToolUnID>"
		"						</VBEF::CritToolType>"
		"						<LogicalOperator>1</LogicalOperator>"
		"					</ElemTypeCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Is Bypass Angle</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Is Orthogonal</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Bypass</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"			</CompositeCriterion>"
		"		</CriterionExpression>";

	rule = SetRuleStyleToRed(rule);

	return rule;
}

API_OverrideRule JHP_WallLength4Rule(API_Guid guid = APINULLGuid)
{
	API_OverrideRule rule = {guid, "API_AUDIT_Wall Length - 1/4\"" };
	
	rule.criterionXML =
		"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
		"<CriterionExpression Mv=\"2\" Sv=\"1\">"
		"			<TextMatchType>1</TextMatchType>"
		"			<Size>1</Size>"
		"			<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"			<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"				<LogicalOperator>2</LogicalOperator>"
		"				<CriteriaCount>5</CriteriaCount>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>B4B7B134-EC56-4D40-8D4C-71D7C5A2493A</ClassGuid>"
		"					<ElemTypeCriterion Mv=\"2\" Sv=\"3\">"
		"						<VBEF::CritToolType Mv=\"1\" Sv=\"0\">"
		"							<ElemRegistryRefId>1463897138</ElemRegistryRefId>"
		"							<ElemCreatorToolUnID>"
		"								<MainGuid>00000000-0000-0000-0000-000000000000</MainGuid>"
		"								<RevGuid>00000000-0000-0000-0000-000000000000</RevGuid>"
		"							</ElemCreatorToolUnID>"
		"						</VBEF::CritToolType>"
		"						<LogicalOperator>1</LogicalOperator>"
		"					</ElemTypeCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Is Bypass Angle</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Tolerance</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>Fine</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Bypass</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Length</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API WALLS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>6</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>/4</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"			</CompositeCriterion>"
		"		</CriterionExpression>";

	rule = SetRuleStyleToRed(rule);

	return rule;
}

API_OverrideRule JHP_WallLength8Rule(API_Guid guid = APINULLGuid)
{
	API_OverrideRule rule = { guid, "API_AUDIT_Wall Length - 1/8\"" };
	rule.criterionXML =
		"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
		"<CriterionExpression Mv=\"2\" Sv=\"1\">"
		"			<TextMatchType>1</TextMatchType>"
		"			<Size>1</Size>"
		"			<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"			<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"				<LogicalOperator>2</LogicalOperator>"
		"				<CriteriaCount>5</CriteriaCount>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>B4B7B134-EC56-4D40-8D4C-71D7C5A2493A</ClassGuid>"
		"					<ElemTypeCriterion Mv=\"2\" Sv=\"3\">"
		"						<VBEF::CritToolType Mv=\"1\" Sv=\"0\">"
		"							<ElemRegistryRefId>1463897138</ElemRegistryRefId>"
		"							<ElemCreatorToolUnID>"
		"								<MainGuid>00000000-0000-0000-0000-000000000000</MainGuid>"
		"								<RevGuid>00000000-0000-0000-0000-000000000000</RevGuid>"
		"							</ElemCreatorToolUnID>"
		"						</VBEF::CritToolType>"
		"						<LogicalOperator>1</LogicalOperator>"
		"					</ElemTypeCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Is Bypass Angle</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Length</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API WALLS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>6</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>/8</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>2</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Tolerance</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>Standard</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Tolerance</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>Fine</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Bypass</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"			</CompositeCriterion>"
		"		</CriterionExpression>";

	rule = SetRuleStyleToRed(rule);

	return rule;
}

API_OverrideRule JHP_WallLengthDecRule(API_Guid guid = APINULLGuid)
{
	API_OverrideRule rule = { guid, "API_AUDIT_Wall Length - Decimal" };
	rule.criterionXML =

		"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
		"<CriterionExpression Mv=\"2\" Sv=\"1\">"
		"			<TextMatchType>1</TextMatchType>"
		"			<Size>1</Size>"
		"			<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"			<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"				<LogicalOperator>2</LogicalOperator>"
		"				<CriteriaCount>4</CriteriaCount>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>B4B7B134-EC56-4D40-8D4C-71D7C5A2493A</ClassGuid>"
		"					<ElemTypeCriterion Mv=\"2\" Sv=\"3\">"
		"						<VBEF::CritToolType Mv=\"1\" Sv=\"0\">"
		"							<ElemRegistryRefId>1463897138</ElemRegistryRefId>"
		"							<ElemCreatorToolUnID>"
		"								<MainGuid>00000000-0000-0000-0000-000000000000</MainGuid>"
		"								<RevGuid>00000000-0000-0000-0000-000000000000</RevGuid>"
		"							</ElemCreatorToolUnID>"
		"						</VBEF::CritToolType>"
		"						<LogicalOperator>1</LogicalOperator>"
		"					</ElemTypeCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Is Bypass Angle</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Length</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API WALLS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>6</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"StringVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>.</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"				<ClassGuid>C6EBD1BD-7702-46FF-8ED9-9CC37648A7C7</ClassGuid>"
		"				<CompositeCriterion Mv=\"2\" Sv=\"1\">"
		"					<LogicalOperator>1</LogicalOperator>"
		"					<CriteriaCount>1</CriteriaCount>"
		"					<ClassGuid>58E4905F-AD57-45F5-8D26-0100000F60BF</ClassGuid>"
		"					<PropertyCriterion Mv=\"5\" Sv=\"0\">"
		"						<VBEF::ConditionIO Mv=\"1\" Sv=\"0\">"
		"							<PropertyDefinitionUserId Version=\"2\">"
		"								<PrimaryId>1</PrimaryId>"
		"								<HasGuidId>false</HasGuidId>"
		"								<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"								<HasNameId>true</HasNameId>"
		"								<Name>API Wall Bypass</Name>"
		"								<PropertyDefinitionGroupUserId Version=\"2\">"
		"									<PrimaryId>1</PrimaryId>"
		"									<HasGuidId>false</HasGuidId>"
		"									<Guid>00000000-0000-0000-0000-000000000000</Guid>"
		"									<HasNameId>true</HasNameId>"
		"									<Name>API AUDITS</Name>"
		"								</PropertyDefinitionGroupUserId>"
		"							</PropertyDefinitionUserId>"
		"							<CriteriaOperatorEnum>0</CriteriaOperatorEnum>"
		"							<Value>"
		"								<Variant Type=\"BoolVariant\">"
		"									<Status>Normal</Status>"
		"									<Value>false</Value>"
		"								</Variant>"
		"							</Value>"
		"						</VBEF::ConditionIO>"
		"					</PropertyCriterion>"
		"				</CompositeCriterion>"
		"			</CompositeCriterion>"
		"		</CriterionExpression>";

	rule = SetRuleStyleToRed(rule);

	return rule;
}

GSErrCode JHP_WallChecker_AddRulesToCombinations(GS::Array<API_Guid> rules)
{
	GSErrCode err = NoError;

	GS::Array<GS::UniString> names;
	names.Push("01_Unit Plans Overall");
	names.Push("02_Unit Plans Enlarged");
	names.Push("20_Building Plan Overall");
	names.Push("21_Building Plan Enlarged Area");
	names.Push("22_Building Plan Enlarged Room");
	names.Push("23_Building Plan Stair and Elevator");

	for (UInt32 i = 0; i < names.GetSize(); ++i)
	{
		GS::Array<API_Guid> comboRules;
		API_OverrideCombination combo = { APINULLGuid, names[i] };
		if (ACAPI_Override_GetOverrideCombination(combo, &comboRules) == NoError)
		{
			comboRules.Append(rules);
			
			err = ACAPI_Override_ChangeOverrideCombination(combo, &comboRules);

			if (err != NoError) { return err; }
		}
	}

	return err;
}



GSErrCode JHP_WallChecker_ImportRules(void)
{
	GSErrCode err = NoError;

	API_OverrideRule wallAngle = JHP_WallAngleRule();
	API_OverrideRule wallLength4 = JHP_WallLength4Rule();
	API_OverrideRule wallLength8 = JHP_WallLength8Rule();
	API_OverrideRule wallLengthDec = JHP_WallLengthDecRule();

	err = ACAPI_Override_CreateOverrideRule(wallAngle);
	if (err == APIERR_NAMEALREADYUSED) 
	{ 
		err = NoError;
		err = ACAPI_Override_GetOverrideRule(wallAngle);
		if (err != NoError) { return err; }
		wallAngle = JHP_WallAngleRule(wallAngle.guid);
		err = ACAPI_Override_ChangeOverrideRule(wallAngle);
		if (err != NoError) { return err; }
	}
	
	err = ACAPI_Override_CreateOverrideRule(wallLength4);
	if (err == APIERR_NAMEALREADYUSED) 
	{ 
		err = NoError;
		err = ACAPI_Override_GetOverrideRule(wallLength4); 
		if (err != NoError) { return err; }
		wallLength4 = JHP_WallLength4Rule(wallLength4.guid);
		err = ACAPI_Override_ChangeOverrideRule(wallLength4);
		if (err != NoError) { return err; }
	}

	err = ACAPI_Override_CreateOverrideRule(wallLength8);
	if (err == APIERR_NAMEALREADYUSED) 
	{ 
		err = NoError;
		err = ACAPI_Override_GetOverrideRule(wallLength8);
		if (err != NoError) { return err; }
		wallLength8 = JHP_WallLength8Rule(wallLength8.guid);
		err = ACAPI_Override_ChangeOverrideRule(wallLength8);
		if (err != NoError) { return err; }
	}

	err = ACAPI_Override_CreateOverrideRule(wallLengthDec);
	if (err == APIERR_NAMEALREADYUSED) 
	{ 
		err = NoError;
		err = ACAPI_Override_GetOverrideRule(wallLengthDec);
		if (err != NoError) { return err; }
		wallLengthDec = JHP_WallLengthDecRule(wallLengthDec.guid);
		err = ACAPI_Override_ChangeOverrideRule(wallLengthDec);
		if (err != NoError) { return err; }
	}

	GS::Array<API_Guid> ruleList;
	ruleList.Push(wallAngle.guid);
	ruleList.Push(wallLength4.guid);
	ruleList.Push(wallLength8.guid);
	ruleList.Push(wallLengthDec.guid);

	err = JHP_WallChecker_AddRulesToCombinations(ruleList);

	//Apply these rules to the correct set of combinations then done!

	return err;
}

