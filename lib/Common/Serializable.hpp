
class Serializable{
public:
	virtual void serialize(std::ostream&) const = 0;
	virtual void deserialize(std::istream&) = 0;
};