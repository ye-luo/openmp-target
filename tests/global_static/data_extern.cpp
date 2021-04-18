template<typename T>
class engine
{
public:
  static const T params[4];
};

extern template class engine<float>;
extern template class engine<double>;

template <>
const float engine<float>::params[4] = {1.0f, 2.0f, 3.0f, 4.0f};

template <>
const double engine<double>::params[4] = {1.0, 2.0, 3.0, 4.0};

template class engine<float>;
template class engine<double>;
