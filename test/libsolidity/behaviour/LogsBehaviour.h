/*
	This file is part of solidity.
	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <map>
#include <set>
#include <test/libsolidity/Behaviour.h>
#include <vector>

namespace solidity::frontend::test
{
class SemanticTest;
class SolidityExecutionFramework;

class LogsBehaviour: public Behaviour
{
public:
	explicit LogsBehaviour(SemanticTest* _test);
	~LogsBehaviour() override = default;

	std::optional<bytes> numLogs(FunctionCall const& _call);
	std::optional<bytes> numLogTopics(FunctionCall const& _call);
	std::optional<bytes> logTopic(FunctionCall const& _call);
	std::optional<bytes> logAddress(FunctionCall const& _call);
	std::optional<bytes> logData(FunctionCall const& _call);
	std::optional<bytes> expectEvent(FunctionCall const& _call);

	void begin() override;
	void after(TestFunctionCall const& _call) override;

	bool isValid(const TestFunctionCall& _call) override;

	void printExpectedResult(const TestFunctionCall& _call, const std::string& _indention, std::ostream& _stream) override;
	void printObtainedResult(const TestFunctionCall& _call, const std::string& _indention, std::ostream& _stream) override;
	void printToFile(const TestFunctionCall& _call, std::ostream& _stream) override;

private:
	SemanticTest* m_test = nullptr;
	SolidityExecutionFramework* m_executionFramework = nullptr;

	std::map<FunctionCall const*, std::vector<LogRecord>> m_producedLogs{};
	std::map<FunctionCall const*, std::set<size_t>> m_touchedLogs;
};

} // namespace  solidity::frontend::test
