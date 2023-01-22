class GGE_data
{
	public:
		GGE_data() = default;
		virtual ~GGE_data() = default;
		enum data_type {CUSTOM, TEXT, NUMBER};

		void* get_data() { return _data; };
		void set_data(void* data, unsigned size) { 
	protected:
		unsigned _size;
		data_type _type;
	private:
		void* _data = nullptr;
};
