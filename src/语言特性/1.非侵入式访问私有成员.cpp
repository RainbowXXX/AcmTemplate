// 原理: static变量初始化的时候存下了成员指针(其实是偏移量)

template <typename Member>
class FPrivateAccess {
public:
	inline static typename Member::Type MemberPtr;
};

template <typename Member, typename Member::Type Ptr>
struct FStaticPtrInit {
	struct FConstructPrivateAccess {
		FConstructPrivateAccess() {
			FPrivateAccess<Member>::MemberPtr = Ptr;
		}
	};
	inline static FConstructPrivateAccess TriggerConstruct;
};

class FTest
{
public:
	int VarB;
	std::uint64_t VarC;
	FTest() { VarA = 0; VarB = 1; };
	int func() {}
private:
	int VarA;
};

struct FTestAccessVarA { using Type = int FTest::*; };
template struct FStaticPtrInit<FTestAccessVarA, &FTest::VarA>;
void Example()
{
	FTest Test;
	FTest* TestPtr = new FTest;
	int varA = Test.*FPrivateAccess<FTestAccessVarA>::MemberPtr;
	int lpVarA = TestPtr->*FPrivateAccess<FTestAccessVarA>::MemberPtr;

	std::cout << varA << std::endl;
	std::cout << lpVarA << std::endl;
}