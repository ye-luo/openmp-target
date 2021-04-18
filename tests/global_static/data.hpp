template<typename T>
class engine
{
public:
  static const T params[4];
};

template <>
const float engine<float>::params[4];

template <>
const double engine<double>::params[4];
