#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

template<typename T>
class RefVectorWithLeader : public std::vector<std::reference_wrapper<T>>
{
public:
  RefVectorWithLeader(T& leader) : leader_(leader) {}

  RefVectorWithLeader(T& leader, const std::vector<std::reference_wrapper<T>>& vec) : leader_(leader)
  {
    for (T& element : vec)
      this->push_back(element);
  }

  T& getLeader() const { return leader_; }

  T& operator[](size_t i) const { return std::vector<std::reference_wrapper<T>>::operator[](i).get(); }

  template<typename CASTTYPE>
  CASTTYPE& getCastedLeader() const
  {
    static_assert(std::is_const<T>::value == std::is_const<CASTTYPE>::value, "Unmatched const type qualifier!");
#ifndef NDEBUG
    assert(dynamic_cast<CASTTYPE*>(&leader_.get()) != nullptr);
#endif
    return static_cast<CASTTYPE&>(leader_.get());
  }

  template<typename CASTTYPE>
  CASTTYPE& getCastedElement(size_t i) const
  {
    static_assert(std::is_const<T>::value == std::is_const<CASTTYPE>::value, "Unmatched const type qualifier!");
#ifndef NDEBUG
    assert(dynamic_cast<CASTTYPE*>(&(*this)[i]) != nullptr);
#endif
    return static_cast<CASTTYPE&>((*this)[i]);
  }

private:
  std::reference_wrapper<T> leader_;
};

class TWF
{
public:
  static void mw_accept_rejectMove(const RefVectorWithLeader<TWF>& wf_list)
  {
    auto& wf_leader = wf_list.getLeader();
    const int vec_size = wf_list.size();
    std::cout << "vec size outside " << vec_size << " addr " << &wf_list << std::endl;
    #pragma omp taskloop default(shared) if(wf_leader.use_tasking)
    for(int i=0; i<2; i++)
    {
      std::cout << "vec size inside " << wf_list.size() << " addr " << &wf_list << std::endl;
      if (vec_size != wf_list.size())
        throw std::runtime_error("mismatched size!");
    }
  }

private:
  bool use_tasking = false;
};

int main()
{
  std::vector<TWF> twf(2);
  std::vector<std::reference_wrapper<TWF>> twf_ref;
  twf_ref.push_back(twf[0]);
  twf_ref.push_back(twf[1]);
  RefVectorWithLeader<TWF> twf_crowd(twf[0], twf_ref);
  TWF::mw_accept_rejectMove(twf_crowd);
  return 0;
}
